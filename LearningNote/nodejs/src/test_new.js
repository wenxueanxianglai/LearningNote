var Vehicle = function()  {
    'use strict';
    this.price = 1000;
};

var v = new Vehicle();
v.price =10;

var s = new Vehicle();

console.log(v);
console.log(s);
