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

```text
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
