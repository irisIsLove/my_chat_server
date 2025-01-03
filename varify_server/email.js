const nodemailer = require('nodemailer')
const configModule = require('./config')

let transport = nodemailer.createTransport({
    host: "smtp.qq.com",
    port: 465,
    secure: true,
    auth: {
        user: configModule.emailUser,
        pass: configModule.emailPass
    }
})

function sendEmail(mailOptions) {
    return new Promise(function (resolve, reject) {
        transport.sendMail(mailOptions, function (error, info) {
            if (error) {
                console.log(error)
                reject(error)
            } else {
                console.log('邮件已成功发送: ' + info.response)
                resolve(info.response)
            }
        })
    })
}

module.exports.sendEmail = sendEmail