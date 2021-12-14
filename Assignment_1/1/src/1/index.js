var canvas = document.getElementById('canvas')
var ctx = canvas.getContext("2d")

// translate to center of canvas
ctx.translate(canvas.width / 2, canvas.height / 4)


// FIRST QUESTION:

var koch = new LSystem({
  axiom: 'G',
  productions: {
    'G': 'X-G-X',
    'X': 'G+Y+G',
    'Y': "[+F]F[-F]"
    //'Y': '+FF-F'
  },
  finals: {
    '+': () => { ctx.rotate((Math.PI / 180) * 30) },
    '-': () => { ctx.rotate((Math.PI / 180) * -30) },
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

koch.iterate(9)
koch.final()