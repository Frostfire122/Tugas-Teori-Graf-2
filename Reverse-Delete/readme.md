## Network Failure Simulations (Reverse-Delete Algorithm)

### Simulation 1: Single Edge Failure (Edge A–G Fails)

To simulate a link failure between **A** and **G**, edge `{0, 6, 5}` is permanently removed (`removed = true`) before the Reverse-Delete loop begins.

**Execution Step-by-Step:**

1. **Sort active edges descending by weight**:
   - `A-F` (10), `F-C` (9), `B-E` (9), `A-B` (7), `B-D` (7), `C-E` (7), `A-C` (6), `G-F` (6), `E-D` (5), `F-E` (5), `B-C` (5)
2. **Evaluate Edges (Heaviest First)**:
   - **REMOVED**: `A-F` (10) -> Graph stays connected
   - **REMOVED**: `F-C` (9) -> Graph stays connected
   - **REMOVED**: `B-E` (9) -> Graph stays connected
   - **REMOVED**: `A-B` (7) -> Graph stays connected
   - **REMOVED**: `B-D` (7) -> Graph stays connected
   - **KEPT**: `C-E` (7) -> Removal disconnects graph; restored
   - **REMOVED**: `A-C` (6) -> Graph stays connected (path to A via C-E-F-G-A remains)
   - **KEPT**: `G-F` (6) -> Critical bridge to reach G; restored
   - **KEPT**: `E-D` (5) -> Critical bridge to reach D; restored
   - **KEPT**: `F-E` (5) -> Restored to maintain component connection
   - **KEPT**: `B-C` (5) -> Critical bridge to reach B; restored
   - **KEPT**: `A-C` (6) -> Restored as bridge to reconnect node A

**Adapted Output:**

    Edge    Weight
    -----------------
    C - E   7
    G - F   6
    A - C   6
    E - D   5
    F - E   5
    B - C   5
    -----------------
    Total MST weight: 34

---

### Simulation 2: Node Failure (Node C Fails)

When node **C** completely fails, all incident edges connected to vertex `2` (`A-C`, `F-C`, `C-E`, `B-C`) are set to `removed = true`. DFS connectivity checks are adjusted to only evaluate the remaining 6 functional nodes (`A`, `B`, `D`, `E`, `F`, `G`).

**Execution Step-by-Step:**

1. **Sort active edges descending (excluding C's edges)**:
   - `A-F` (10), `B-E` (9), `A-B` (7), `B-D` (7), `G-F` (6), `E-D` (5), `F-E` (5), `A-G` (5)
2. **Evaluate Edges (Heaviest First)**:
   - **REMOVED**: `A-F` (10) -> Graph stays connected via A-G-F
   - **REMOVED**: `B-E` (9) -> Graph stays connected via B-D-E
   - **KEPT**: `A-B` (7) -> Critical bridge to reach node B; restored
   - **REMOVED**: `B-D` (7) -> Graph stays connected via E-D
   - **KEPT**: `G-F` (6) -> Critical bridge connecting {A, G} to {F, E, D}; restored
   - **KEPT**: `E-D` (5) -> Critical bridge to reach node D; restored
   - **KEPT**: `F-E` (5) -> Critical bridge connecting F to E; restored
   - **KEPT**: `A-G` (5) -> Critical bridge connecting A to G; restored

**Adapted Output:**

    Edge    Weight
    -----------------
    A - B   7
    G - F   6
    E - D   5
    F - E   5
    A - G   5
    -----------------
    Total MST weight: 28
