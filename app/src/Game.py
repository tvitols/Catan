'''
Main code for integrating different components and running the game itself
'''

from flask_socketio import emit
from gameio import read, write, interact_with_process, kill
import asyncio

class Game:

    def __init__(self):
        self.loop = asyncio.new_event_loop()
        self.run = self.loop.run_until_complete
        self.process = self.run(interact_with_process())
        
    def kill(self):
        self.run(kill(self.process))
        self.loop.close()

    def readGame(self):
        self.run(read(self.process.stdin))
