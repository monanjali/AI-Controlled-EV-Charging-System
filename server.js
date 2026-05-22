const express = require('express');
const fs = require('fs');
const path = require('path');
const app = express();
const port = 3000;
const dataFile = path.join(__dirname, 'public', 'data.json');
app.use(express.static(path.join(__dirname,'public')));
app.use(express.json());
app.get('/data.json',(req,res)=>{
const data = fs.readFileSync(dataFile);
res.setHeader('Content-Type','application/json');
res.send(data);
});
app.post('/api/voltage',(req,res)=>{
const {solar,dc} = req.body;
if(typeof solar === 'number' && typeof dc === 'number'){
const data = {solar,dc,timestamp:new Date()};
fs.writeFileSync(dataFile,JSON.stringify(data));
res.json({success:true});
}
else{
res.status(400).json({error:"Invalid data"});

}
});
app.listen(port,()=>{
console.log(`Server running at http://localhost:${port}`);
});