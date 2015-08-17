var numBlocks = 100;
var numFuncs = 100;

var body = [];

body.push("{");
var indentation = "\t";

for (var i = 0; i < numBlocks; i++) {
	body.push(indentation + "LDINT 1");
	body.push(indentation + "LDINT 2");
	body.push(indentation + "ADD");
	body.push(indentation + "POP");
}

body.push(indentation + "RET");
body.push("}");

var bodyStr = body.join("\n");

console.log("func main() Int");
console.log("{");
console.log("\tLDINT 1337");
console.log("\tRET");
console.log("}");
console.log("")

for (var i = 0; i < numFuncs; i++) {
	var funcStr = "func large" + i + "() Void\n";
	funcStr += bodyStr;
	console.log(funcStr);
	console.log("");
}