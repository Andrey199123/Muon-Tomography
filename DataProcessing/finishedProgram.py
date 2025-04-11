import pandas as pd
import numpy as np
import pyvista as pv
import time

LAYER_DEFINITIONS = {
    3: {"name": "Waste Matrix",     "range": (0, 800),     "color": "brown"},
    2: {"name": "Inner Liner",      "range": (800, 850),   "color": "blue"},
    1: {"name": "Outer Steel Shell","range": (950, 1250),  "color": "gray"},
}

def load_data(csv_path):
    df = pd.read_csv(csv_path)
    df = df[(df["KineticEnergy(MeV)"] > 0.1) & (df["KineticEnergy(MeV)"] < 1.0)]
    df["radius"] = np.sqrt(df["PosX(mm)"] ** 2 + df["PosY(mm)"] ** 2)
    return df[(df["radius"] >= 0) & (df["radius"] <= 1250)]

def plot_layers(layer_ids, csv_path):
    df = load_data(csv_path)
    plotter = pv.Plotter(window_size=[1024, 768])

    for layer_id in layer_ids:
        if layer_id not in LAYER_DEFINITIONS:
            print(f"❌ Invalid layer ID: {layer_id}")
            continue

        layer_info = LAYER_DEFINITIONS[layer_id]
        rmin, rmax = layer_info["range"]
        color = layer_info["color"]
        name = layer_info["name"]

        hits = df[(df["radius"] >= rmin) & (df["radius"] < rmax)]

        if hits.empty:
            print(f"⚠️ No hits found in {name} (Layer {layer_id})")
            continue

        points = np.column_stack((hits["PosX(mm)"], hits["PosY(mm)"], hits["PosZ(mm)"]))
        cloud = pv.PolyData(points)
        plotter.add_mesh(cloud, color=color, point_size=1.2, opacity=0.5, render_points_as_spheres=True)

    plotter.add_title(f"Layers: {', '.join(str(i) for i in layer_ids)}")
    plotter.show_grid()
    plotter.show()



plot_layers([1,2], "/home/dhavarajamanikandan/Downloads/stepData.csv")


#change the path to the path of the csv file in this folder
