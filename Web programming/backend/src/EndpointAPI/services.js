const {
    Files,
} = require('../data');

const add = async (fileName, fileHash, fileSize) => {

    const file = new Files({
        fileName,
        fileHash,
        fileSize
    });

    await file.save();

};

const check = async (fileName, fileHash, fileSize) => {

    let file = Files.find().find({ fileName, fileHash, fileSize });

    return file;

};

const getAll = async () => {

    let files = await Files.find();

    return files;

};

const getById = async (id) => {

    return await Files.findById(id);

};

const updateById = async (id, fileName, fileHash, fileSize) => {

    await Files.findByIdAndUpdate(id, { fileName, fileHash, fileSize });

};

const deleteById = async (id) => {

    await Files.findByIdAndDelete(id);

};

module.exports = {
    add,
    check,
    getAll,
    getById,
    updateById,
    deleteById
}