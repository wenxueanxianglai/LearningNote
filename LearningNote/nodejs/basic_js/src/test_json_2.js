const fs = require("fs");

let jsPerson = {
    pageSet: []
}

//let arrMeeting = ["90019168", "40019166", "60019167", "90019169", "60019170", "50019171", "90019173", "70019172", "30019174"];

let arrMeeting = ["90019168", "40019166", "60019167"];

//let curMeetNumer = 1;
for (let iter = 10106, curMeetNumer = 1; iter < 10200; ++iter, ++curMeetNumer) {
    let onePerson = {
        userName : "15500010105",
        password : "123456",
        getwayIP : "172.17.201.177",
        port: "20045",
        meetingID: "90019168",
        isSpeak : 1
    };

    if (arrMeeting.length * 9 >= curMeetNumer) {
        onePerson.userName = "155000" + iter.toString();
        onePerson.meetingID = arrMeeting[parseInt((curMeetNumer-1)/9)];
        onePerson.isSpeak = curMeetNumer % 9 == 0 ? 0 : 1;
        jsPerson.pageSet.push(onePerson);
    }
    else {
        break;
    }
}

person = JSON.stringify(jsPerson);
console.log(person);

fs.writeFile('config_src.json', person, err => {
    if(err) console.log('write File failed');
})