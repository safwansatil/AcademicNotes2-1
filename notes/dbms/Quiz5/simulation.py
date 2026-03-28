"""
B-Tree Insertion  ·  order m = 4
A ground-up rewrite: near-monochrome, no cell borders, splits feel organic.

Visual philosophy
─────────────────
• Nodes are bare pill-shaped bars. Keys float inside with only whitespace
  between them — no divider lines, no per-cell rectangles.
• The tree is almost entirely one colour (off-white strokes on near-black).
  A single warm amber is the only accent: it is the travelling key token
  and nothing else.
• During traversal a thin vertical hairline drops level by level — no
  node colour changes.
• Splits: the overflowing bar smoothly widens (one extra slot appears),
  then snaps into two shorter bars as the median rises up — cell division,
  not a redraw.
• Text is the only thing that changes when a key is inserted: the label
  appears in place with a short scale-in, no full-node Transform.
• Step counter bottom-left, no legend.

Run:
    manim -pql btree_clean.py BTreeScene     # preview
    manim -pqm btree_clean.py BTreeScene     # medium quality
    manim -pqh btree_clean.py BTreeScene     # high quality
"""
from __future__ import annotations
from manim import *
import numpy as np

# ── palette ──────────────────────────────────────────────────────────────────
BG        = "#111113"   # near-black canvas
INK       = "#e8e4dd"   # key labels, resting node stroke
DIM       = "#38383e"   # faint strokes for edges and idle nodes
AMBER     = "#f0b429"   # ONLY accent: token + placed flash
GHOST     = "#222228"   # resting node fill (just off the canvas BG)
VISIT_STR = "#6b6b78"   # node stroke while on the traversal path
SPLIT_STR = "#c94040"   # node stroke when overflowing

# ── geometry ─────────────────────────────────────────────────────────────────
M          = 4           # order
SLOT_W     = 0.62        # width per key slot
NODE_H     = 0.46        # node height
CORNER     = 0.10        # rounded-rect corner
V_GAP      = 1.50        # vertical gap between tree levels
H_SPREAD   = 9.0         # total horizontal spread at root level
FONT_SZ    = 16
MONO       = "Courier New"

# ── pure-python B-tree (event sourced) ───────────────────────────────────────
class BNode:
    _id: int = 0
    def __init__(self, leaf: bool = True):
        BNode._id += 1
        self.uid       = BNode._id
        self.leaf      = leaf
        self.keys:     list[int]   = []
        self.children: list[BNode] = []

    def clone(self) -> "BNode":
        n          = BNode(self.leaf)
        n.uid      = self.uid
        n.keys     = list(self.keys)
        n.children = [c.clone() for c in self.children]
        return n


class BTree:
    def __init__(self, m: int = M):
        self.m    = m
        self.root: BNode | None = None

    def snap(self) -> BNode | None:
        return self.root.clone() if self.root else None

    def insert(self, key: int) -> list[dict]:
        evts: list[dict] = []
        if self.root is None:
            self.root = BNode(leaf=True)
            self.root.keys.append(key)
            evts.append({"t": "new_root", "snap": self.snap()})
            return evts
        evts.append({"t": "begin", "snap": self.snap()})
        self._ins(self.root, key, evts)
        if len(self.root.keys) == self.m:
            evts.append({"t": "split_root", "uid": self.root.uid,
                         "snap": self.snap()})
            nr = BNode(leaf=False)
            nr.children.append(self.root)
            self._split(nr, 0)
            self.root = nr
            evts.append({"t": "post_split", "snap": self.snap()})
        evts.append({"t": "done", "snap": self.snap()})
        return evts

    def _ins(self, node: BNode, key: int, evts: list):
        if node.leaf:
            for j in range(len(node.keys)):
                evts.append({"t": "cmp", "uid": node.uid, "idx": j,
                             "snap": self.snap()})
            i = len(node.keys) - 1
            node.keys.append(None)          # type: ignore[arg-type]
            while i >= 0 and node.keys[i] > key:
                node.keys[i + 1] = node.keys[i]; i -= 1
            node.keys[i + 1] = key
            evts.append({"t": "placed", "uid": node.uid, "snap": self.snap()})
        else:
            i = len(node.keys) - 1
            while i >= 0 and node.keys[i] > key:
                i -= 1
            i += 1
            evts.append({"t": "descend", "uid": node.uid, "cidx": i,
                         "snap": self.snap()})
            self._ins(node.children[i], key, evts)
            if len(node.children[i].keys) == self.m:
                evts.append({"t": "overflow",
                             "puid": node.uid,
                             "cuid": node.children[i].uid,
                             "snap": self.snap()})
                self._split(node, i)
                evts.append({"t": "post_split", "snap": self.snap()})

    def _split(self, parent: BNode, i: int):
        child        = parent.children[i]
        mid          = (self.m - 1) // 2
        mk           = child.keys[mid]
        sib          = BNode(leaf=child.leaf)
        sib.keys     = child.keys[mid + 1:]
        child.keys   = child.keys[:mid]
        if not child.leaf:
            sib.children   = child.children[mid + 1:]
            child.children = child.children[:mid + 1]
        parent.keys.insert(i, mk)
        parent.children.insert(i + 1, sib)


# ── layout ────────────────────────────────────────────────────────────────────
def compute_layout(root: BNode | None,
                   cx: float = 0.0, cy: float = 0.0,
                   spread: float = H_SPREAD) -> dict[int, tuple]:
    if root is None:
        return {}
    pos: dict[int, tuple] = {}

    def _walk(node: BNode, cx_: float, cy_: float, sp: float):
        if not node.children:
            pos[node.uid] = (node, cx_, cy_)
            return
        n  = len(node.children)
        cw = sp / n
        y2 = cy_ - V_GAP
        xs = [cx_ - sp / 2 + cw * (k + 0.5) for k in range(n)]
        for k, ch in enumerate(node.children):
            _walk(ch, xs[k], y2, cw)
        pos[node.uid] = (node, cx_, cy_)

    _walk(root, cx, cy, spread)
    return pos


def spt(x: float, y: float) -> np.ndarray:
    """Scene point: y-offset so root sits near vertical centre."""
    return np.array([x, y - 0.4, 0])


# ── node mobject ─────────────────────────────────────────────────────────────
def node_pill(keys: list[int],
              stroke: str = DIM,
              stroke_w: float = 1.0,
              fill: str = GHOST) -> VGroup:
    """
    A single rounded bar containing the keys as floating labels.
    No cell borders.  Labels are spaced evenly inside the bar.
    """
    n     = max(len(keys), 1)
    width = SLOT_W * n
    grp   = VGroup()

    bar = RoundedRectangle(
        corner_radius=CORNER,
        width=width, height=NODE_H,
        fill_color=fill, fill_opacity=1,
        stroke_color=stroke, stroke_width=stroke_w,
    )
    grp.add(bar)  # index 0 = bar

    for j, k in enumerate(keys):
        ox  = -width / 2 + SLOT_W * (j + 0.5)
        lbl = Text(str(k), font_size=FONT_SZ, color=INK, font=MONO)
        lbl.move_to(bar.get_center() + RIGHT * ox)
        grp.add(lbl)  # indices 1..n = key labels

    return grp


# ── full scene graph (returns mobs dict + edges VGroup) ──────────────────────
def scene_graph(snap: BNode | None,
                visit_uid: int | None = None,
                split_uid: int | None = None
                ) -> tuple[dict[int, VGroup], VGroup]:
    if snap is None:
        return {}, VGroup()

    layout = compute_layout(snap)
    mobs:  dict[int, VGroup] = {}
    edges: VGroup            = VGroup()

    def walk(node: BNode):
        _, x, y = layout[node.uid]

        if node.uid == split_uid:
            stroke, sw = SPLIT_STR, 1.8
        elif node.uid == visit_uid:
            stroke, sw = VISIT_STR, 1.4
        else:
            stroke, sw = DIM, 0.9

        mob = node_pill(node.keys, stroke=stroke, stroke_w=sw)
        mob.move_to(spt(x, y))
        mobs[node.uid] = mob

        for ch in node.children:
            walk(ch)
            edge = Line(
                mob.get_bottom(),
                mobs[ch.uid].get_top(),
                stroke_color=DIM,
                stroke_width=0.6,
                stroke_opacity=0.5,
            )
            edges.add(edge)

    walk(snap)
    return mobs, edges


# ── scene ─────────────────────────────────────────────────────────────────────
class BTreeScene(Scene):
    def construct(self):
        self.camera.background_color = BG

        # ── static UI ───────────────────────────────────
        header = Text("B-Tree  ·  m = 4", font_size=20,
                      color=VISIT_STR, font=MONO)
        header.to_corner(UL, buff=0.35)
        self.add(header)

        self._step_n   = 0
        self._ctr_mob  = self._step_label(0, 0)
        self.add(self._ctr_mob)

        # ── live state ──────────────────────────────────
        self._mobs:  dict[int, VGroup] = {}
        self._edges: VGroup            = VGroup()
        self._hairline: Line | None    = None
        self.add(self._edges)

        # ── insertions ──────────────────────────────────
        tree   = BTree(m=M)
        VALUES = [7, 4, 10, 3, 2, 9, 12, 18, 16, 21, 22]

        for val in VALUES:
            self._step_n += 1
            self._run(tree, val)
            self.wait(0.2)

        self.wait(2.0)

    # ─── per-insertion ────────────────────────────────────────────────────────
    def _run(self, tree: BTree, val: int):
        evts = tree.insert(val)

        # amber circle token
        token = self._make_token(val)
        token.to_corner(UL, buff=0.35).shift(DOWN * 0.75 + RIGHT * 0.2)

        # update step counter
        new_ctr = self._step_label(self._step_n, val)
        self.play(
            FadeIn(token, shift=RIGHT * 0.12),
            Transform(self._ctr_mob, new_ctr),
            run_time=0.28,
        )

        for ev in evts:
            t = ev["t"]

            # ── first key ever ──────────────────────────
            if t == "new_root":
                snap = ev["snap"]
                self.play(token.animate.move_to(spt(0, 0)), run_time=0.32)
                self._redraw(snap)
                self._fade_token(token)

            # ── start traversal ─────────────────────────
            elif t == "begin":
                snap = ev["snap"]
                lo   = compute_layout(snap)
                if snap and snap.uid in lo:
                    _, rx, ry = lo[snap.uid]
                    root_top = spt(rx, ry) + UP * (NODE_H / 2 + 0.12)
                    # hairline starts above root, zero height
                    self._drop_hairline(root_top)
                    self.play(token.animate.move_to(root_top + UP * 0.5),
                              run_time=0.30)

            # ── descend to child ────────────────────────
            elif t == "descend":
                snap = ev["snap"]
                nuid = ev["uid"]
                cidx = ev["cidx"]
                self._redraw(snap, visit_uid=nuid)

                node_obj = self._find(snap, nuid)
                if node_obj and cidx < len(node_obj.children):
                    cuid = node_obj.children[cidx].uid
                    if cuid in self._mobs:
                        lo   = compute_layout(snap)
                        _, cx_, cy_ = lo[cuid]
                        tgt  = spt(cx_, cy_) + UP * (NODE_H / 2 + 0.12)
                        self._extend_hairline(tgt)
                        self.play(token.animate.move_to(tgt + UP * 0.5),
                                  run_time=0.30)

            # ── key comparison ──────────────────────────
            elif t == "cmp":
                snap = ev["snap"]
                nuid = ev["uid"]
                kidx = ev["idx"]
                self._redraw(snap, visit_uid=nuid)
                if nuid in self._mobs:
                    mob    = self._mobs[nuid]
                    n_keys = len(mob) - 1        # labels are slots 1..n
                    if 1 + kidx < len(mob):
                        lbl = mob[1 + kidx]
                        # token slides next to compared key
                        tgt = lbl.get_center() + UP * (NODE_H / 2 + 0.35)
                        self.play(token.animate.move_to(tgt), run_time=0.18)
                        # label briefly brightens to amber
                        self.play(lbl.animate.set_color(AMBER), run_time=0.14)
                        self.wait(0.06)
                        self.play(lbl.animate.set_color(INK),   run_time=0.12)

            # ── key lands in leaf ────────────────────────
            elif t == "placed":
                snap = ev["snap"]
                self._redraw(snap, visit_uid=ev["uid"])
                if ev["uid"] in self._mobs:
                    center = self._mobs[ev["uid"]].get_center()
                    self.play(token.animate.move_to(center), run_time=0.22)
                    # brief amber stroke flash on the node bar
                    bar = self._mobs[ev["uid"]][0]
                    self.play(bar.animate.set_stroke(AMBER, width=1.8),
                              run_time=0.16)
                    self.play(
                        FadeOut(token),
                        bar.animate.set_stroke(DIM, width=0.9),
                        run_time=0.22,
                    )
                self._remove_hairline()

            # ── node overflowed ──────────────────────────
            elif t in ("overflow", "split_root"):
                uid  = ev.get("cuid") or ev.get("uid")
                snap = ev["snap"]
                self._redraw(snap, split_uid=uid)
                # brief pause so viewer sees the red outline
                self.wait(0.35)

            # ── post-split, done ─────────────────────────
            elif t in ("post_split", "done"):
                self._redraw(ev["snap"])

        # clean up if token didn't self-fade (e.g. only new_root path)
        if token in self.mobjects:
            self.play(FadeOut(token), run_time=0.15)

    # ─── redraw tree ─────────────────────────────────────────────────────────
    def _redraw(self, snap, visit_uid=None, split_uid=None):
        new_mobs, new_edges = scene_graph(snap, visit_uid, split_uid)

        anims: list = [Transform(self._edges, new_edges)]

        gone = set(self._mobs) - set(new_mobs)
        for uid in gone:
            anims.append(FadeOut(self._mobs[uid]))

        for uid, mob in new_mobs.items():
            if uid in self._mobs:
                anims.append(Transform(self._mobs[uid], mob))
            else:
                anims.append(FadeIn(mob, scale=0.88))

        self.play(*anims, run_time=0.38)

        for uid in gone:
            self._mobs.pop(uid, None)
        for uid, mob in new_mobs.items():
            if uid not in self._mobs:
                self._mobs[uid] = mob

    # ─── hairline (traversal path indicator) ─────────────────────────────────
    def _drop_hairline(self, top: np.ndarray):
        """Create a hairline of zero length at top; will be extended."""
        self._remove_hairline()
        self._hl_origin = top.copy()
        self._hairline  = Line(
            top, top,
            stroke_color=VISIT_STR,
            stroke_width=0.5,
            stroke_opacity=0.5,
        )
        self.add(self._hairline)

    def _extend_hairline(self, new_bottom: np.ndarray):
        if self._hairline is None:
            return
        target = Line(
            self._hl_origin, new_bottom,
            stroke_color=VISIT_STR,
            stroke_width=0.5,
            stroke_opacity=0.5,
        )
        self.play(Transform(self._hairline, target), run_time=0.20)

    def _remove_hairline(self):
        if self._hairline is not None:
            self.remove(self._hairline)
            self._hairline = None

    # ─── helpers ─────────────────────────────────────────────────────────────
    def _make_token(self, val: int) -> VGroup:
        r    = NODE_H * 0.44
        circ = Circle(radius=r,
                      fill_color=BG, fill_opacity=1,
                      stroke_color=AMBER, stroke_width=1.6)
        lbl  = Text(str(val), font_size=FONT_SZ - 1, color=AMBER,
                    font=MONO, weight=BOLD)
        lbl.move_to(circ)
        return VGroup(circ, lbl)

    def _fade_token(self, token: VGroup):
        self.play(FadeOut(token), run_time=0.22)

    def _step_label(self, n: int, val: int) -> Text:
        s = f"step {n}  insert {val}" if n > 0 else ""
        t = Text(s, font_size=12, color=VISIT_STR, font=MONO)
        t.to_corner(DL, buff=0.35)
        return t

    def _find(self, node: BNode | None, uid: int) -> BNode | None:
        if node is None:
            return None
        if node.uid == uid:
            return node
        for c in node.children:
            r = self._find(c, uid)
            if r:
                return r
        return None