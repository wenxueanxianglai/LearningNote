function Shape() {
  this.x = 0;
  this.y = 0;
}

Shape.prototype.move = function (x, y) {
  this.x += x;
  this.y += y;
  console.info("Shape moved.");
};

// First
function Rectangle() {
  Shape.call(this); // 调用父类构造
}

function Rectangle() {
  this.base = Shape;
  this.base();
}

// second
Rectangle.prototype = Object.create(Shape.prototype);
Rectangle.prototype.constructor = Rectangle;
