function Student(props) {
  this.name = props.name || "Unnamed";
}

Student.prototype.hello = function () {
  alert("Hello, " + this.name + "!");
};

// 继承
function PrimaryStudent(props) {
  Student.call(this, props);
  this.grade = props.grade;
}

// 修改继承关系    F  --> Student.prototype
function F() {}
F.prototype = Student.prototype;

PrimaryStudent.prototype = new F();

PrimaryStudent.prototype.constructor = PrimaryStudent;
// 继续在PrimaryStudent原型（就是new F()对象）上定义方法：
PrimaryStudent.prototype.getGrade = function () {
  return this.grade;
};

// 创建xiaoming:
var xiaoming = new PrimaryStudent({
  name: "小明",
  grade: 2,
});

console.log(xiaoming);
