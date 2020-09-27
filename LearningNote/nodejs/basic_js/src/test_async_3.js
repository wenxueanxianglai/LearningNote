console.log("start");

function loginUser(email, password, callback) {
  setTimeout(() => {
    console.log("Now we have the data");
    callback({ userEmail: email });
  }, 5000);
}

const user = loginUser("dev@qq.com", 12345, (user) => {
  console.log(user);
});

console.log("Finish");
