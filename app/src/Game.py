'''
Main code for integrating different components and running the game itself
'''

from flask_socketio import emit
from os import subprocess


def new_game():
    subprocess.run(["python", "app.py"], capture_output=True)

def load_game(save_data):
    subprocess.run(["./src/catan", save_data], capture_output=True)