import zmq
import json
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from quaternion_example import generate_sphere

# Configure ZeroMQ context and socket
context = zmq.Context()
socket = context.socket(zmq.SUB)

# Replace with your ZeroMQ server's address
zmq_server_address = "tcp://127.0.0.1:5555"
socket.connect(zmq_server_address)

# Subscribe to all messages
socket.setsockopt_string(zmq.SUBSCRIBE, "")

# Initialize 3D plot
fig = plt.figure()
sphere_points = generate_sphere()
sphere_points *= 6371
ax = fig.add_subplot(111, projection='3d')
ax.plot_surface(
    sphere_points[..., 0], sphere_points[..., 1], sphere_points[..., 2],
    color='b', alpha=0.6
)
ax.set_title("3D Position Data")
ax.set_xlabel("X")
ax.set_ylabel("Y")
ax.set_zlabel("Z")

# Enable interactive mode for live updates
plt.ion()
plt.show()

cnt=0
try:
    while True:
        # Receive a message from ZeroMQ
        message = socket.recv_string()
        cnt += 1
        if cnt > 100:
            break 
        # Parse the JSON message into x, y, z data
        try:
            data = json.loads(message)
            x, y, z = data["x"], data["y"], data["z"]
        except (json.JSONDecodeError, KeyError):
            print("Received malformed message, skipping:", message)
            continue

        # Clear the plot and update with new data
        ax.cla()
        ax.set_title("3D Position Data")
        ax.set_xlabel("X")
        ax.set_ylabel("Y")
        ax.set_zlabel("Z")
        ax.scatter(x, y, z, c='r', marker='o')
        ax.plot_surface(
            sphere_points[..., 0], sphere_points[..., 1], sphere_points[..., 2],
            color='b', alpha=0.6
        )

        # Redraw the plot
        plt.draw()
        plt.pause(0.01)

except KeyboardInterrupt:
    print("Terminating...")
finally:
    socket.close()
    context.term()

