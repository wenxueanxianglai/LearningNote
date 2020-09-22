var obj = {};
console.log(obj);

obj.__proto__.zxpTestMyQ = 1;



function Foo(name, age) {
  this.name = name;
}
var f = new Foo("Zx");
f.printName = function () {
  console.log(this.name);
};

// proto 的链条 以及 proto与prototype关系
console.log(obj.__proto__ === Object.prototype);    // obj的 proto指向 object的prototype
console.log(f.__proto__ === Foo.prototype);     // f的 proto 指向 Foo.prototype
console.log(obj.__proto__ === Foo.prototype.__proto__)
console.log(f.zxpTestMyQ);      // 证明 顶层的对象实例也就一个
console.log(f);

// prototype 与 constructor
console.log(Foo === Foo.prototype.constructor)      // 默认函数的 constructor 指向 函数本身
console.log(Foo);
f.printName();
f.toString();
