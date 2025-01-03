const fs = require('fs');

let config = JSON.parse(fs.readFileSync('config.json', 'utf8'))
let emailUser = config.email.user
let emailPass = config.email.pass
let mysqlHost = config.mysql.host
let mysqlPort = config.mysql.port
let mysqlPass = config.mysql.pass
let redisHost = config.redis.host
let redisPort = config.redis.port

module.exports = {
    emailUser,
    emailPass,
    mysqlHost,
    mysqlPort,
    mysqlPass,
    redisHost,
    redisPort
}
