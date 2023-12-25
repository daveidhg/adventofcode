import sympy

# Had to use sympy for this one ¯\_(ツ)_/¯, I'm not doing this manually in c++ ,`)

hailstones = [list(map(int, line.replace("@", ',').split(','))) for line in open("2023/24/input.txt")]

equations = []

xs, ys, zs, vxs, vys, vzs = sympy.symbols("xs, ys, zs, vxs, vys, vzs")

for i in range(10): # Using 10 to make sure we are not getting a lucky match elsewhere.
    px, py, pz, vx, vy, vz = hailstones[i]
    equations.append((xs - px) * (vy - vys) - (ys - py) * (vx - vxs))
    equations.append((ys - py) * (vz - vzs) - (zs - pz) * (vy - vys))
    # Transitive rule says if these x -> y equations and y -> z equations are equal, x -> z is also equal.

answers = sympy.solve(equations)
print(f"Part two: {answers[0][xs] + answers[0][ys] + answers[0][zs]}")
