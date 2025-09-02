import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation

class NBodySim():
    def __init__(self, fig, ax, num_particles = 3, min = -1000, max = 1000, mass = 100, G = 10):
        self.num_particles = num_particles
        self.min = min
        self.max = max
        self.mass = mass
        self.G = G
        self.fig = fig
        self.ax = ax
        self.ax.set_xlim(self.min, self.max)
        self.ax.set_ylim(self.min, self.max)

        self.particles = np.random.uniform(self.min, self.max, (self.num_particles * 2)).reshape((2, self.num_particles))
        #print(self.particles)
        self.accelerations = np.zeros_like(self.particles)
        self.velocities = np.zeros_like(self.particles)

    def calculate_force_vectors(self):
        self.accelerations.fill(0)
        for i in range(self.num_particles):
            for j in range(i+1, self.num_particles):
                d_x = self.particles[0][j] - self.particles[0][i]
                d_y = self.particles[1][j] - self.particles[1][i]

                r = (d_x) ** 2 + (d_y) ** 2
                a = self.G * self.mass / (r + 1e-5)
                theta = np.arctan(d_y / d_x)
                theta += np.pi if d_x < 0 else 0

                self.accelerations[0][i] += a * np.cos(theta)
                self.accelerations[1][i] += a * np.sin(theta)
                self.accelerations[0][j] -= a * np.cos(theta)
                self.accelerations[1][j] -= a * np.sin(theta)
        #print(self.accelerations)

    def step(self):
        self.velocities += self.accelerations
        self.particles += self.velocities

    def show(self):
        self.ax.clear()
        self.ax.set_xlim(self.min, self.max)
        self.ax.set_ylim(self.min, self.max)
        self.ax.scatter(self.particles[0], self.particles[1])
        self.fig.canvas.draw()
        

    def simulate(self, frame):
        self.calculate_force_vectors()
        self.step()
        self.show()

def main():
    fig, ax = plt.subplots()
    sim = NBodySim(fig, ax)
    anim = FuncAnimation(fig, sim.simulate)
    plt.show()

if __name__ == '__main__':
    main()