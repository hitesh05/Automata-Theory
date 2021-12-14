var canvas = document.getElementById('canvas')
var ctx = canvas.getContext("2d")

// translate to center of canvas
ctx.translate(canvas.width / 2, canvas.height / 4)

// SECOND QUESTION:

var koch = new LSystem({
  axiom: 'X',
  productions: {
    'X': 'F[-X]X[+X][+X]F-[-X]+X[-X]',
    'F': 'FF'
    // 'Y': '+FF-F'
  },
  finals: {
    '+': () => { ctx.rotate((Math.PI / 180) * -15) },
    '-': () => { ctx.rotate((Math.PI / 180) * 15) },
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

koch.iterate(4)
koch.final()