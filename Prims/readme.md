## Network Failure Simulations

### Simulation 1: Single Edge Failure (Edge A–G Fails)

To simulate a link disconnection between **A** and **G**, the edge weight is set to zero (`graph[0][6] = 0` and `graph[6][0] = 0`).

**Execution Step-by-Step:**

1. **Start at A**: `key[A]=0`. Available connections: `C` (6), `B` (7), `F` (10). *(G is bypassed due to weight 0)*
2. **Pick C (6)**: Parent is `A`. Updates keys: `B` (5 via C), `E` (7 via C), `F` (9 via C).
3. **Pick B (5)**: Parent is `C`. Updates key: `D` (7 via B).
4. **Pick E (7)**: Parent is `C`. Updates keys: `D` (5 via E), `F` (5 via E).
5. **Pick D (5)**: Parent is `E`.
6. **Pick F (5)**: Parent is `E`. Updates key: `G` (6 via F).
7. **Pick G (6)**: Parent is `F`.

**Adapted Output:**

    Edge    Weight
    -----------------
    A - C   6
    C - B   5
    C - E   7
    E - D   5
    E - F   5
    F - G   6
    -----------------
    Total MST weight: 34

---

### Simulation 2: Node Failure (Node C Fails)

When node **C** suffers a complete breakdown, all incident connections on row `2` and column `2` are zeroed out (`graph[2][v] = 0` and `graph[u][2] = 0`). The algorithm dynamically re-routes around node C using alternative paths.

**Execution Step-by-Step:**

1. **Start at A**: `key[A]=0`. Available connections: `G` (5), `B` (7), `F` (10). *(C is ignored as all its edge weights are 0)*
2. **Pick G (5)**: Parent is `A`. Updates key: `F` (6 via G).
3. **Pick F (6)**: Parent is `G`. Updates key: `E` (5 via F).
4. **Pick E (5)**: Parent is `F`. Updates keys: `D` (5 via E), `B` (9 via E).
5. **Pick D (5)**: Parent is `E`. Updates key: `B` (7 via D).
6. **Pick B (7)**: Parent is `D`.

**Adapted Output:**

    Edge    Weight
    -----------------
    A - G   5
    G - F   6
    F - E   5
    E - D   5
    D - B   7
    -----------------
    Total MST weight: 28
