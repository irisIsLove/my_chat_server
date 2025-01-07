const configModule = require('./config.json');
const Redis = require('ioredis');

const RedisClient = new Redis.Redis(
    {
        host: configModule.redis.hostm,
        port: configModule.redis.port,
        password: configModule.redis.pass
    }
)

RedisClient.on('error', function (err) {
    console.log('RedisClient connect Error')
    RedisClient.quit()
})

async function getRedis(key) {
    try {
        const result = await RedisClient.get(key)
        if (result == null) {
            console.log('result: ', '<' + result + '>', 'This key cannot be found...')
            return null
        }
        console.log('result: ', '<' + result + '>', 'Get key successfully!')
        return result
    } catch (error) {
        console.log('getRedis error is ', error)
        return null
    }
}

async function queryRedis(key) {
    try {
        const result = await RedisClient.exists(key)
        if (result == 0) {
            console.log('result: ', '<' + result + '>', 'This key cannot be found...')
            return null
        }
        console.log('result: ', '<' + result + '>', 'Get key successfully!')
        return result
    } catch (error) {
        console.log('queryRedis error is ', error)
        return null
    }
}

async function setRedisExpire(key, value, expire) {
    try {
        await RedisClient.set(key, value)
        await RedisClient.expire(key, expire)
        return true
    } catch (error) {
        console.log('setRedisExpire error is ', error)
        return false
    }
}

function quit() {
    RedisClient.quit()
}

module.exports = { getRedis, queryRedis, setRedisExpire, quit }
