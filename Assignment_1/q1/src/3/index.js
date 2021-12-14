var canvas = document.getElementById('canvas')
var ctx = canvas.getContext("2d")

// translate to center of canvas
ctx.translate(canvas.width / 2, canvas.height / 4)

// THIRD QUESTION:

var koch = new LSystem({
    axiom: 'X',
    finals: {
        '+': () => { ctx.rotate((Math.PI / 180) * 12.5) },
        '-': () => { ctx.rotate((Math.PI / 180) * -12.5) },
        'X': () => {
            ctx.beginPath()
            ctx.moveTo(0, 0)
            ctx.lineTo(0, 40 / (koch.iterations + 1))
            ctx.stroke()
            ctx.translate(0, 40 / (koch.iterations + 1))
        },
        'F': () => {
            ctx.beginPath()
            ctx.moveTo(0, 0)
            ctx.lineTo(0, 40 / (koch.iterations + 1))
            ctx.stroke()
            ctx.translate(0, 40 / (koch.iterations + 1))
        },
        '[': () => {
            ctx.save();
        },
        ']': () => {
            ctx.restore();
        }
    },
})

koch.setProduction('X', {
    successors: [
        { weight: 50, successor: 'F-[[-X]+X]+F[+FX]-X' },
        { weight: 50, successor: 'F+[[+X]-X]-F[-FX]+X[X]' }
    ]
})

koch.setProduction('F', {
    successors: [
        { weight: 33, successor: 'F[F]F' },
        { weight: 33, successor: 'F[+]F' },
        { weight: 33, successor: 'F[FF]F' }
    ]
})

koch.iterate(4)
koch.final()