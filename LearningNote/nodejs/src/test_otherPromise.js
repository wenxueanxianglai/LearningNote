console.log('AAAA');
setTimeout(() => console.log('BBBB'), 1000); // t1
const start = new Date();
while (new Date() - start < 3000) {}
console.log('CCCC');
setTimeout(() => console.log('DDDD'), 0);  // t2
new Promise((resolve, reject) => {
  console.log('EEEE');
  foo.bar(100);
})
  .then(() => console.log('FFFF'))
  .then(() => console.log('GGGG'))
  .catch(() => console.log('HHHH'));
console.log('IIII');