function myNew(constrc, ...args) {
    const obj = {};                     // 创建一个对象
    obj.__proto__ = constrc.prototype;  // 将obj 的proto属性 指向构造函数的原型对象
    const result = constrc.apply(obj, args);    // constrc 执行的 this 绑定在obj上，并执行
    return result instanceof Object ? result : obj;
}

function Person(name, age) {
    this.name = name;
    this.age = age;
}

const person1 = myNew(Person, 'Tom', 20);
console.log(person1);