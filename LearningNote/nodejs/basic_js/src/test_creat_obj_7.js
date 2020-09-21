function Cat(name) {
  this.name = name;
}

Cat.prototype.say = function () {
  console.log("Hello, ", this.name + "!");
  return "Hello, ", this.name + "!";
};

var kitty = new Cat("Kitty");
var doraemon = new Cat("哆啦A梦");

console.log(typeof kitty.say);
console.log(typeof kitty.say === doraemon.say);

if (
  kitty &&
  kitty.name === "Kitty" &&
  kitty.say &&
  typeof kitty.say === "function" &&
  kitty.say() === "Hello, Kitty!"
) {
  console.log("测试通过!");
} else {
  console.log("测试失败!");
}
