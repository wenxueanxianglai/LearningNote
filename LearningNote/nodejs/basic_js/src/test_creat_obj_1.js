function create_persion(name, age) {
  let obj = {
    name: name,
    age: age,
    getName: function () {
      console.log(obj.name);
    },
  };

  return obj;
}

(function run() {
  var obj1 = create_persion("dd", 12);
  var obj2 = create_persion("aa", 22);

  obj1.getName();
  obj2.getName();
})();
