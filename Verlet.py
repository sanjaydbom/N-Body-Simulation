import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
from matplotlib import axes

class WrongArrayDimError(ValueError):
    pass

class NBodySim():
    def __init__(self, fig, ax: axes._axes.Axes, num_particles = 10, min = -10000, max = 10000, mass = 100, G = 100, time_step = 1, positions = None, velocities = None, radius = 100):
        self.fig = fig
        self.ax = ax

        #basic config
        self.num_particles = num_particles
        self.min = min
        self.max = max
        self.mass = mass
        self.dt = time_step
        self.G = G
        self.radius = radius
        self.friction = 0

        self.ax.set_xlim(self.min, self.max)
        self.ax.set_ylim(self.min, self.max)

        #check for positions
        if isinstance(positions, np.ndarray):
            if positions.shape[0] != 2:
                raise WrongArrayDimError(f"Expected position array with shape (2, num_particles), got {positions.shape}")
            self.position = positions
            self.num_particles = positions.shape[1]
        elif positions is not None:
            raise TypeError(f"Error, expected NumPy array for positions, got {type(positions)}")
        else:
            self.position = np.random.uniform(self.min, self.max, (2,self.num_particles)).reshape((2,self.num_particles))
            print(self.position)

        #check for velocities
        if isinstance(velocities, int):
            self.velocities = np.full((2, self.num_particles), velocities)
        elif isinstance(velocities, np.ndarray):
            if velocities.shape == self.position.shape:
                self.velocities = velocities
            else:
                raise WrongArrayDimError(f"Error, expected NumPy array of shape {self.position.shape} for velocities, got NumPy array of shape {velocities.shape}")
        elif velocities is not None:
            raise TypeError(f"Error, expected NumPy array for velocities, got {type(velocities)}")
        else:
            self.velocities = np.zeros_like(self.position)

        self.accelerations = np.zeros_like(self.position)
        custom_color = np.random.rand(self.num_particles) * 255
        self.scatter = ax.scatter(self.position[0], self.position[1], s = self.radius, c=custom_color)
        self.calculate_acceleration()

    def update_velocity(self):
        #Only updates a half step
        self.velocities = self.accelerations * self.dt / 2 + self.velocities


    def update_position(self):
        self.position += self.velocities * self.dt
        self.collision_check()

    def collision_check(self):
        #m1 * v1_i + m2 * v2_i = m1 * v1_f + m2 * v2_f
        #0.5 * m1 * (v1_i) ** 2 + 0.5 * m2 * (v2_i) ** 2 = 0.5 * m1 * (v1_f) ** 2 + 0.5 * m2 * (v2_f) ** 2
        #v1_f = (m1 * v1_i + m2 * v2_i - m2 * v2_f) / m1
        #v1_f = sqrt(2 * (0.5 * m1 * (v1_i) ** 2 + 0.5 * m2 * (v2_i) ** 2 - 0.5 * m2 * (v2_f) ** 2) / m1)
        #(m1 * v1_i + m2 * v2_i - m2 * v2_f) / m1 = sqrt(2 * (0.5 * m1 * (v1_i) ** 2 + 0.5 * m2 * (v2_i) ** 2 - 0.5 * m2 * (v2_f) ** 2) / m1)
        #
        for i in range(self.num_particles):
            for j in range(i+1, self.num_particles):
                if np.sqrt((self.position[0][i] - self.position[0][j]) ** 2 + (self.position[1][i] - self.position[1][j]) ** 2) < 2.01 * self.radius: 

                    new_X_basis_vector = np.array([self.position[0][j] - self.position[0][i], self.position[1][j] - self.position[1][i]])
                    new_X_basis_vector = new_X_basis_vector / np.sqrt(np.sum(np.square(new_X_basis_vector)))
                    new_Y_basis_vector = np.array([new_X_basis_vector[1], -new_X_basis_vector[0]])

                    v1_x_i = np.dot(np.array([self.velocities[0][i], self.velocities[1][i]]), new_X_basis_vector)
                    v1_y = np.dot(np.array([self.velocities[0][i], self.velocities[1][i]]), new_Y_basis_vector)
                    v2_x_i = np.dot(np.array([self.velocities[0][j], self.velocities[1][j]]), new_X_basis_vector)
                    v2_y = np.dot(np.array([self.velocities[0][j], self.velocities[1][j]]), new_Y_basis_vector)
                    
                    v1_x_f = v2_x_i
                    v2_x_f = v1_x_i
                    
                    v1_f = np.array([v1_x_f, v1_y])
                    v2_f = np.array([v2_x_f, v2_y])

                    self.velocities[0][i] = v1_f[0] * new_X_basis_vector[0] + v1_f[1] * new_Y_basis_vector[0]
                    self.velocities[1][i] = v1_f[0] * new_X_basis_vector[1] + v1_f[1] * new_Y_basis_vector[1]
                    self.velocities[0][j] = v2_f[0] * new_X_basis_vector[0] + v2_f[1] * new_Y_basis_vector[0]
                    self.velocities[1][j] = v2_f[0] * new_X_basis_vector[1] + v2_f[1] * new_Y_basis_vector[1]
                    self.update_position()
                    '''
                    dist = np.sqrt((self.position[0][i] - self.position[0][j]) ** 2 + (self.position[1][i] - self.position[1][j]) ** 2)
                    dist_to_add = self.radius - dist / 2 + 1e-3
                    self.position[0][i] -= dist_to_add * new_X_basis_vector[0]
                    self.position[1][i] -= dist_to_add * new_X_basis_vector[1]
                    self.position[0][j] += dist_to_add * new_X_basis_vector[0]
                    self.position[1][j] += dist_to_add * new_X_basis_vector[1]'''

    def calculate_acceleration(self):
        self.accelerations.fill(0)
        for i in range(self.num_particles):
            for j in range(i+1, self.num_particles):
                dx = self.position[0][j] - self.position[0][i]
                dy = self.position[1][j] - self.position[1][i]

                r = dx ** 2 + dy ** 2
                #F = ma => a = F / m = G * m_1 * m_2 /(r * m_1) = G * m_2 / r
                a = self.G * self.mass / (r + 1e-5)

                theta = np.arctan2(dy, dx)

                #Newton's third law
                self.accelerations[0][i] += a * np.cos(theta)
                self.accelerations[1][i] += a * np.sin(theta)
                self.accelerations[0][j] -= a * np.cos(theta)
                self.accelerations[1][j] -= a * np.sin(theta)

    def step(self):
        self.update_velocity()
        self.update_position()
        self.calculate_acceleration()
        self.update_velocity()
    
    def simulate(self, frame):
        self.step()
        new_positions = np.vstack((self.position[0], self.position[1])).T
        self.scatter.set_offsets(new_positions)
        return self.scatter,

def main():
    fig, ax = plt.subplots()
    plt.grid()
    plt.title("N-Body Simulation")
    sim = NBodySim(fig, ax, 2)
    anim = FuncAnimation(fig, sim.simulate, interval=20, blit=True)
    plt.show()

if __name__ == '__main__':
    main()
        