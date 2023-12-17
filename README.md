# Amazon Delivery Truck Scheduling and Route Optimization

This project focuses on optimizing delivery truck routes for Amazon's logistics network. It employs sophisticated algorithms to schedule deliveries and optimize routes for multiple trucks, addressing the complexities of the Multiple Traveling Salesman Problem (mTSP). The code base is written in C++ for backend processing and Python for data visualization.

## Steps to Compile and Run Code

Ensure the following tools and libraries are installed to run the code:

### Prerequisites:

- **C++ Compiler**: A modern C++ compiler (C++11 or newer) is required.
- **Python**: Python 3.7 or later is recommended.
- **Libraries**: `notebook`, `pandas`, `plotly`, `ipywidgets`. These can be installed using `pip`.

### Compilation and Execution:

1. **Compile C++ code**: In the terminal, navigate to the project directory and execute:
   ```
   make
   ```
   This command compiles the C++ code.

2. **Run the compiled program**: After successful compilation, run the program using:
   ```
   ./program
   ```
   This executes the program, generating routes and schedules for the trucks, and outputs the results to CSV files (`route_data.csv` and `delivery_route.csv`).

### Visualization:

For data visualization, two Jupyter notebooks are provided:

- `RouteBarGraph.ipynb`: Visualizes the total distances traveled by each truck using bar graphs.
- `Route_Scatter_Plot.ipynb`: Displays scatter plots of the truck routes for each day.

Open these notebooks in a Jupyter environment to view the visualizations.

## Overview of the Project

This project is an advanced implementation of route optimization techniques, primarily focusing on the mTSP. It is tailored to Amazon's delivery network, aiming to efficiently schedule and route multiple delivery trucks.

### Features:

- **Route Optimization**: Implements Greedy Nearest Neighbor and Lin-Kernighan algorithms to optimize routes.
- **Schedule Management**: Manages delivery requests and truck assignments, ensuring feasible delivery schedules.
- **Visualization**: Offers interactive visualizations for analyzing the efficiency of different routing algorithms.

### Usage:

This project is ideal for logistics companies, especially those similar to Amazon, looking to optimize their delivery schedules and routes. It demonstrates practical applications of mTSP and advanced routing heuristics.

### Conclusion:

This project showcases an effective blend of algorithmic complexity and practical application in the realm of logistics and delivery services. It exemplifies how sophisticated algorithms can significantly improve operational efficiency in a real-world context, particularly for large-scale delivery networks.

For detailed documentation, refer to the provided source files and Jupyter notebooks.
