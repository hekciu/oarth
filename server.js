const http = require("http");
const fs = require("fs");

const files = ['./index.html', './out.wasm'];

const server = http.createServer((req, res) => {
    let filePath = '.' + req.url;

    if (filePath === './') {
        filePath = './index.html';
    }

    if (!files.includes(filePath)) {
        res.writeHead(404);
        res.end();
        return;
    }

    const fileContent = fs.readFileSync(filePath);

    const contentType = filePath.endsWith('wasm') ? 'application/wasm' : 'text/html';

    res.writeHead(200, { 'Content-Type': contentType });
    res.end(fileContent, 'utf-8');
})

server.listen((3000), () => {
    console.log("Server is Running");
})
