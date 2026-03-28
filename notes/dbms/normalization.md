```text
Start with your relation
    ↓
Is every cell atomic? ──NO──→ Fix to 1NF first
    ↓ YES
Is every non-prime fully dependent on entire key? ──NO──→ Not in 2NF
    ↓ YES (in 2NF)
Do any non-prime attributes determine other non-prime? ──YES──→ Not in 3NF
    ↓ NO (in 3NF)
For every FD, is left side a superkey? ──NO──→ In 3NF but NOT in BCNF
    ↓ YES
BCNF! 
```