## Coupling and Cohesion
Think in a kitchen,
Coupling: how dependent modules are on each other
loosely coupled: u can open the knife drawer to get a knife
tightly coupled: u have to open the spice drawer then the knife drawer to get a knife
Cohesion: how related the things in a module are
high cohesion: knife drawer only has knives
low cohesion: knife is kept within spices and other unrelated items

```text
Low Cohesion (Bad) ←---→ High Cohesion (Good)
Does many unrelated things    Does ONE thing well
```
```text
Tight Coupling (Bad) ←---→ Loose Coupling (Good)
Too many dependencies    Minimal dependencies
```

A well-designed system exhibits high cohesion (each component has a single, clear responsibility) and loose coupling (components interact through well-defined interfaces with minimal knowledge of each other's internals).
