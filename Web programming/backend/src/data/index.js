const mongoose = require('mongoose');

(async () => {
    try {
        await mongoose.connect(`mongodb://docker:docker@mongo:27017/docker?authSource=admin`,
            {
                useNewUrlParser: true,
                useUnifiedTopology: true
            }
        );
    } catch (e) {
        console.trace(e);
    }
})();

const Files = require('./models/Files');

module.exports = {
    Files
}