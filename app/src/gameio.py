import asyncio

async def read(stream):
    # print("Reading from process...")
    out = await stream.read(2048)
    print(out.decode(), end='')

async def write(stream, input_data):
    # print(input_data, end='')
    stream.write(input_data.encode("utf-8"))
    # print("Write complete.")
    await stream.drain()

async def interact_with_process():
    process = await asyncio.create_subprocess_shell(
        "/home/tvitols/CatanDev/Catan/build/Catan",
        stdin=asyncio.subprocess.PIPE,
        stdout=asyncio.subprocess.PIPE,
        stderr=asyncio.subprocess.PIPE
    )


    return process

async def kill(proc):
    await proc.wait()