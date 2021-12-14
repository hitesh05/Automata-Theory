var canvas = document.getElementById('canvas')
var ctx = canvas.getContext("2d")

// translate to center of canvas
ctx.translate(canvas.width / 2, canvas.height / 4)

// FOURTH QUESTION:

var koch = new LSystem({
    axiom: 'F+F',
    productions: {
        'F': 'F - F + + F - F',
        'F<F>-F': 'F - + F + F'
    },
    finals: {
        '+': () => { ctx.rotate((Math.PI / 180) * 90) },
        '-': () => { ctx.rotate((Math.PI / 180) * -90) },
        'F': () => {
            ctx.beginPath()
            ctx.moveTo(0, 0)
            ctx.lineTo(0, 5 / (koch.iterations + 1))
            ctx.stroke()
            ctx.translate(0, 5 / (koch.iterations + 1))
        },
        '[': () => {
            ctx.save();
        },
        ']': () => {
            ctx.restore();
        }
    },
})

koch.iterate(9)
koch.final()