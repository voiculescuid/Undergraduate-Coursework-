const mongoose = require('mongoose');

const Schema = mongoose.Schema;

const FileSchema = new Schema({
    fileName: {
        type: String,
        required: true
    },
    fileHash: {
        type: String,
        required: true
    },
    fileSize: {
        type: Number,
        required: true
    }
}, { timestamps: true });

const FileModel = mongoose.model('Files', FileSchema);

module.exports = FileModel;
