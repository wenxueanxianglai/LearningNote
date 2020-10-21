let wr = {
    id : '1234',
    str : 'hahahah'
};


let wwr = {
    id: '1234222',
    rrr: 'sertt',
    str : 'hahahah111111'
};

let arrwr = [wr, wwr ];
console.log(arrwr);

arrwr.length

let index_0 = arrwr.findIndex(function (elem) {
    return elem.id == '1234'
})

let index_1 = arrwr.findIndex(function (elem) {
    return elem.id == '1234222'
})

arrwr.splice(index_0, 1);

let mapwr = new Map();
mapwr.set(wr.id, wr);
mapwr.set(wwr.id, wwr);


mapwr.forEach((value, key) => { 
    console.log(value);
});

console.log(mapwr);

mapwr.delete(wwr.id);

console.log(mapwr);
mapwr.forEach((value, key) => { 
    console.log(value);
});



