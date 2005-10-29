#-*- coding: ISO-8859-1 -*-

import psp
import gu

import math, struct

def log(fmt, *args):
    file('trace.txt', 'a+').write((fmt % args) + '\n')

def normalize(x, y, z):
    sz = math.sqrt(x*x + y*y + z*z)
    if sz > 0.001:
        sz = 1.0 / sz
    return (x * sz, y * sz, z * sz)

def main():
    ROWS = 64
    COLS = 64

    indices = [0 for unused in xrange((ROWS + 1) * (COLS + 1) * 6)]
    vertices = [None for unused in xrange(ROWS * COLS)]

    for i in xrange(ROWS):
        di = 1.0 * i / ROWS
        s = di * 2 * math.pi
        v = (math.cos(s), math.cos(s), math.sin(s))

        for j in xrange(COLS):
            idx = (j + i * COLS) * 6
            i1 = (i + 1) % ROWS
            j1 = (j + 1) % COLS

            t = 1.0 * j / COLS * math.pi * 2

            v2 = (v[0] * math.cos(t), v[1] * math.sin(t), v[2])

            if v2[0] > 0:
                v3x = min(v2[0] * 10, 1.0)
            else:
                v3x = max(v2[0] * 10, -1.0)

            if v2[1] > 0:
                v3y = min(v2[1] * 10, 1.0)
            else:
                v3y = max(v2[1] * 10, -1.0)

            if v2[2] > 0:
                v3z = min(v2[2] * 10, 1.0)
            else:
                v3z = max(v2[2] * 10, -1.0)

            v3 = v3x, v3y, v3z

            vertices[j + i * COLS] = ((0xFF000000 | (int(abs(v2[0])*255) << 16) | (int(abs(v2[1])*255) << 8) | int(abs(v2[2])*255),
                                       v2, v2),
                                      (0xFF000000 | (int(abs(v2[0])*255) << 16) | (int(abs(v2[1])*255) << 8) | int(abs(v2[2])*255),
                                       normalize(v3x, v3y, v3z), v3))

            indices[idx] = j + i * COLS
            indices[idx + 1] = j1 + i * COLS
            indices[idx + 2] = j + i1 * COLS
            indices[idx + 3] = j1 + i * COLS
            indices[idx + 4] = j1 + i1 * COLS
            indices[idx + 5] = j + i1 * COLS

    # Now build the buffer...

    bf_indices = ''.join([struct.pack('H', k) for k in indices])
    bf_vertices = ''.join([struct.pack('IffffffIffffff',
                                       v1[0], v1[1][0], v1[1][1], v1[1][2], v1[2][0], v1[2][1], v1[2][2],
                                       v2[0], v2[1][0], v2[1][1], v2[1][2], v2[2][0], v2[2][1], v2[2][2]) for v1, v2 in vertices])

    # Let the fun begin

    BUF_WIDTH = 512
    SCR_WIDTH = 480
    SCR_HEIGHT = 272

    kernel = psp.kernel.Kernel()
    display = psp.display.Display()

    kernel.DcacheWritebackAll()

    gu.init()
    ctx = gu.Context()
    gu.start(ctx, gu.DIRECT)
    gu.drawBuffer(gu.PSM_8888, 0, BUF_WIDTH)
    gu.dispBuffer(SCR_WIDTH, SCR_HEIGHT, 0x88000, BUF_WIDTH)
    gu.depthBuffer(0x110000, BUF_WIDTH)
    gu.offset(2048 - (SCR_WIDTH // 2), 2048 - (SCR_HEIGHT // 2))
    gu.viewport(2048, 2048, SCR_WIDTH, SCR_HEIGHT)
    gu.depthRange(0xc350, 0x2710)
    gu.scissor(0, 0, SCR_WIDTH, SCR_HEIGHT)
    gu.enable(gu.SCISSOR_TEST)
    gu.depthFunc(gu.GEQUAL)
    gu.enable(gu.DEPTH_TEST)
    gu.frontFace(gu.CW)
    gu.shadeModel(gu.SMOOTH)
    gu.enable(gu.CULL_FACE)
    gu.enable(gu.LIGHTING)
    gu.enable(gu.LIGHT0)
    gu.finish()
    gu.sync()

    display.waitVblankStart()
    gu.display(1)

    projection = gu.Matrix()
    view = gu.Matrix()
    world = gu.Matrix()

    val = 0

    while True:
        lpos = (1, 0, 1)

        gu.start(ctx, gu.DIRECT)

        gu.clearColor(0xff554433)
        gu.clearDepth(0)
        gu.light(0, gu.DIRECTIONAL, gu.DIFFUSE_AND_SPECULAR, lpos)
        gu.lightColor(0, gu.DIFFUSE_AND_SPECULAR, 0xffffffff)
        gu.clear(gu.COLOR_BUFFER_BIT | gu.DEPTH_BUFFER_BIT)
        gu.specular(12.0)

        projection.identity()
        projection.projection(75.0, 16.0 / 9, 0.5, 1000.0)
        gu.setMatrix(gu.PROJECTION, projection)

        view.identity()
        gu.setMatrix(gu.VIEW, view)

        world.identity()
        world.translate(0.0, 0.0, -2.5)
        world.rotate(val * 0.79 * math.pi / 180,
                     val * 0.98 * math.pi / 180,
                     val * 1.32 * math.pi / 180)
        gu.setMatrix(gu.MODEL, world)

        gu.ambientColor(0xffffffff)

        gu.morphWeight(0, 0.5 * math.sin(val * math.pi / 180) + 0.5)
        gu.drawArray(gu.TRIANGLES,
                     gu.COLOR_8888 | gu.NORMAL_32BITF | gu.VERTEX_32BITF | gu.VERTICES(2) | gu.INDEX_16BIT | gu.TRANSFORM_3D,
                     len(indices), bf_indices, bf_vertices)

        gu.finish()
        gu.sync()

        display.waitVblankStart()
        gu.swapBuffers()

        val += 1

try:
    main()
except KeyboardInterrupt:
    pass
except Exception, e:
    log('%s - %s', e.__class__.__name__, str(e))
