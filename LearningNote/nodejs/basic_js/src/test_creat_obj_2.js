function persion(name, age) {
  this.name = name;
  this.age = age;
  this.getName = function () {
    console.log(this.name);
  };
}

(function run() {
  //   var obj4 = persion("ddds", 33);
  //   obj4.getName();
  var obj1 = new persion("aaa", 12);
  var obj2 = new persion("ddd", 22);
  obj1.getName();
  obj2.getName();
})();
