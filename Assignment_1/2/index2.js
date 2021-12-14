var canvas = document.getElementById('canvas')
var ctx = canvas.getContext("2d")


// translate to center of canvas

ctx.translate(canvas.width / 2, canvas.height / 4)
// let counter=0;
// let initNum;
// let dataObject;

// let Lsys = new LSystem({
//   axiom: '$X',
//   productions: {
//     'X': 'F[+X]X[-X]FX',
//     'F': 'FF'
//   },
//   finals: {
//     '+': () => { ctx.rotate((Math.PI / 180) * 60) },
//     '-': () => { ctx.rotate((Math.PI / 180) * -60) },
//     '$': () => { ctx.rotate((Math.PI / 180) * 180) },
//     'X': () => {
//       ctx.beginPath()
//       ctx.moveTo(0, 0)
//       ctx.lineTo(0, 40 / (Lsys.iterations + 1))
//       ctx.stroke()
//       ctx.translate(0, 40 / (Lsys.iterations + 1))
//     },
//     'F': () => {
//       ctx.beginPath()
//       ctx.moveTo(0, 0)
//       ctx.lineTo(0, 40 / (Lsys.iterations + 1))
//       ctx.stroke()
//       ctx.translate(0, 40 / (Lsys.iterations + 1))
//     },
//     '[': () => { ctx.save() },
//     ']': () => { ctx.restore() }
//   },
// })
// // randomNum()
// Lsys.iterate(2)
// // Lsys.iterate(3)
// Lsys.final()

// const abc = JSON.stringify(LSys);
// console.log(`${ abc }`)

let Lsys = new LSystem({
        axiom: '-F',
        productions: {'F' : 'F-F++F-F'},
  finals: {
    '+': () => { ctx.rotate((Math.PI/180) * -75) },
    '-': () => { ctx.rotate((Math.PI/180) * 75)},
    'F': () => {
        ctx.beginPath()
        ctx.moveTo(0,0)
        ctx.lineTo(0, 40/(Lsys.iterations + 1))
        ctx.stroke()
        ctx.translate(0, 40/(Lsys.iterations + 1))},

    '[': ()=>{ ctx.save()},
    ']':()=>{ctx.restore()}
    // '[': ()=>{ },
    // ']':()=>{}
   }
})
// randomNum()
Lsys.iterate(3)
// Lsys.iterate(3)
Lsys.final()