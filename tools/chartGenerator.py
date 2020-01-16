import plotly.graph_objects as go
import numpy as np

dir_names = ["elitist_selection", "tournament_based_selection", "wheel_of_fortune_selection"]
files = ["a280.out", "berlin52.out", "kroe100.out"]
data = []

for current_dir in dir_names:
    for file_path in files:
        file = open("../" + current_dir + "/" + file_path, "r")

        data = [float(line[0:-1]) for line in file.readlines()]
        
        fig = go.Figure(data=go.Scatter(x=[i for i in range(1, 15)], y=data))
        fig.write_html(current_dir + "_" + file_path + ".html")