const fs = require("fs");

const arrMeeting = ["90019168", "40019166", "60019167"];
const defaultGateWayIp = "172.17.201.177";
const defaultPort = "20045";
const personPerMeeting = 9;
const phoneSection = "155000";

class creatJson {
  constructor(begin, end) {
    this.arrPerson = { pageSet: [] };
    this.begin = begin;
    this.end = end;
  }

  build(fileName, newGateway, newPort) {
    let bTwoGateway = !(!!(typeof newGateway == "undefined") || !!(typeof newPort == "undefined"));
    for (
      let iter = this.begin, curMeetNumer = 1;
      iter < this.end;
      ++iter, ++curMeetNumer
    ) {
      let onePerson = {
        userName: "15500010105",
        password: "123456",
        getwayIP: defaultGateWayIp,
        port: defaultPort,
        meetingID: "90019168",
          isSpeak: 1,
        level: 3
      };

      if (arrMeeting.length * personPerMeeting >= curMeetNumer) {
        onePerson.userName = phoneSection + iter.toString();
        onePerson.meetingID =
          arrMeeting[parseInt((curMeetNumer - 1) / personPerMeeting)];
        if (bTwoGateway) {
          onePerson.isSpeak = curMeetNumer % personPerMeeting == 0 ? 0 : 1;
          if (onePerson.isSpeak == 0) {
            onePerson.getwayIP = newGateway;
            onePerson.port = newPort;
          }
        }

        this.arrPerson.pageSet.push(onePerson);
      } else {
        break;
      }
    }

    if (!(typeof fileName == "undefined")) {
        this.saveAs(fileName);
    }
  }

  saveAs(fileName) {
    let person = JSON.stringify(this.arrPerson);
    console.log(person);

    fs.writeFile(fileName, person, (err) => {
      if (err) console.log("write File failed");
    });
  }
}

function test_sample() {
    let testSample = new creatJson(10106, 10200);
    testSample.build("sample_json.json");
}

function test_twoGateWay() {
    let testTwo = new creatJson(10106, 10200);
    testTwo.build("two_gateway.json", "192.168.1.155", "3000");
}
test_sample();

//test_twoGateWay();