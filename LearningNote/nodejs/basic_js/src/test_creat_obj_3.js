function persion(name, age) {
  this.name = name;
  this.age = age;
  this.getName = function () {
    console.log(this.name);
  };
}

persion.prototype.color = "black";

(function () {
  var per1 = new persion("he", 23);
  var per2 = new persion("she", 13);

  console.log(per1.color);
  console.log(per2.color);
})();
