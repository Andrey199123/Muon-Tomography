import pandas as pd
import numpy as np
import pyvista as pv


df = pd.read_csv("/home/dhavarajamanikandan/Downloads/stepData.csv")
df.sort_values(by=["TrackID", "StepNumber"], inplace=True)


energy_min = 0.5
energy_max = 1.0

energy_hits = df[(df["KineticEnergy(MeV)"] >= energy_min) & (df["KineticEnergy(MeV)"] <= energy_max)]

entry_exit_hits = energy_hits.groupby("TrackID").agg(
    first_hit=("StepNumber", "min"),
    last_hit=("StepNumber", "max")
).reset_index()

first_hits = pd.merge(entry_exit_hits[["TrackID", "first_hit"]],
                      energy_hits,
                      left_on=["TrackID", "first_hit"],
                      right_on=["TrackID", "StepNumber"])

last_hits = pd.merge(entry_exit_hits[["TrackID", "last_hit"]],
                     energy_hits,
                     left_on=["TrackID", "last_hit"],
                     right_on=["TrackID", "StepNumber"])

container_hits = pd.concat([first_hits, last_hits])

x = container_hits["PosX(mm)"].values
y = container_hits["PosY(mm)"].values
z = container_hits["PosZ(mm)"].values
energy = container_hits["KineticEnergy(MeV)"].values
norm_energy = (energy - energy.min()) / (energy.max() - energy.min())

points = np.column_stack((x, y, z))
cloud = pv.PolyData(points)
cloud["Energy"] = norm_energy

plotter = pv.Plotter()
plotter.add_mesh(cloud, scalars="Energy", point_size=1.0, render_points_as_spheres=True, cmap="plasma")
plotter.show_grid()
plotter.show()
