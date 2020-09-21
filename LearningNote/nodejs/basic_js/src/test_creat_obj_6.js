var arr = [1, 2, 3];
var d = 1;

function Student(name) {
  this.name = name;
  this.hello = function () {
    alert("Hello, " + this.name + "!");
  };
}

var xiaoming = new Student("小明");
xiaoming.name; // '小明'
xiaoming.hello(); // Hello, 小明!
