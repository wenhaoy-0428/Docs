// setup canvas

const canvas = document.querySelector('canvas');
const ctx = canvas.getContext('2d');

const width = canvas.width = window.innerWidth;
const height = canvas.height = window.innerHeight;

const numBalls = 30;
// function to generate random number

function random(min, max) {
  const num = Math.floor(Math.random() * (max - min + 1)) + min;
  return num;
}

// function to generate random color

function randomRGB() {
  return `rgb(${random(0, 255)},${random(0, 255)},${random(0, 255)})`;
}

class Shape {
  constructor(x, y, xVel, yVel) {
    // x and y coordinates.
    this.x = x;
    this.y = y;
    // horizontal and vertical velocity.
    this.xVel = xVel;
    this.yVel = yVel;
  }
}

class Ball extends Shape {
  constructor(x, y, xVel, yVel, color, size) {
    super(x, y, xVel, yVel);
    this.color = color;
    // radius
    this.size = size;
    this.exists = true;
  }
  draw() {
    // start to draw a shape.
    ctx.beginPath();
    ctx.lineWidth = 3;
    // define color of the shape.
    ctx.fillStyle = this.color;
    // define the shape is a circle.
    ctx.arc(this.x, this.y, this.size, 0, 2 * Math.PI);
    // render the path
    ctx.fill();
  }

  update() {
    if ((this.x + this.size) >= width || (this.x - this.size) <= 0) {
      this.xVel = -(this.xVel);
    }
  
    if ((this.y + this.size) >= height || (this.y - this.size) <= 0) {
      this.yVel = -(this.yVel);
    }
    this.x += this.xVel;
    this.y += this.yVel;
  }

  collisionDetect() {
    for (const ball of balls) {
      if ((this !== ball) && ball.exists) {
        const dx = this.x - ball.x;
        const dy = this.y - ball.y;
        const distance = Math.sqrt(dx * dx + dy * dy);
  
        if (distance < this.size + ball.size) {
          ball.color = this.color = randomRGB();
        }
      }
    }
  }
}

class EvilCircle extends Shape {
  constructor(x, y) {
    super(x, y, 20, 20);
    this.size = 10;
    this.color = "white";

    window.addEventListener("keydown", (e) => {
      console.log(e.key);
      switch (e.key) {
        case "ArrowLeft":
          // left
          this.x -= this.xVel;
          break;
        case "ArrowUp":
          // up
          this.y -= this.yVel;
          break;
        case "ArrowRight":
          // right
          this.x += this.xVel;
          break;
        case "ArrowDown":
          // down
          this.y += this.yVel;
          break;
      }
    })
  }

  draw() {
    ctx.beginPath();
    ctx.strokeStyle = this.color;
    ctx.arc(this.x, this.y, this.size, 0, 2 * Math.PI);
    ctx.stroke();
  }


  checkBounds() {
    if ((this.x + this.size) >= width) {
      this.x -= this.size;
    }
    if ((this.x + this.size) <= 0) {
      this.x += this.size();
    }
    if ((this.y + this.size) >= height) {
      this.y -= this.size;
    }
    if ((this.y + this.size) <= 0) {
      this.y += this.size();
    }
  }

  collisionDetect() {
    for (const ball of balls) {
      if (ball.exists) {
        const dx = this.x - ball.x;
        const dy = this.y - ball.y;
        const distance = Math.sqrt(dx * dx + dy * dy);
  
        if (distance < this.size + ball.size) {
          ball.exists = false;
        }
      }
    }
  }

}

const evil = new EvilCircle(20, 20, 20, 20);
const balls = [];

while (balls.length < numBalls) {
  const size = random(10, 20);
  const ball = new Ball(
    // ball position always drawn at least one ball width
    // away from the edge of the canvas, to avoid drawing errors
    random(0 + size, width - size),
    random(0 + size, height - size),
    random(-7, 7),
    random(-7, 7),
    randomRGB(),
    size
  );

  balls.push(ball);
}

function loop() {
  // ? Don't know what this is 
  ctx.fillStyle = "rgba(0, 0, 0, 1)";
  // ! If this is not provided, snakes are produced.
  ctx.fillRect(0, 0, width, height);
  evil.draw();
  evil.checkBounds();
  evil.collisionDetect();  
  for (const ball of balls) {
    if (ball.exists) {
      ball.draw();
      ball.update();
      ball.collisionDetect();
    }
  }
  // infinite loop
  requestAnimationFrame(loop);
}
loop();
