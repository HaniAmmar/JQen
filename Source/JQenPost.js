const LoadJQenRender = () => {
    return JQenModule().then((i) => {
        i.JQenRender = i.cwrap(
            "JQenRender",
            "string",
            ["string", "number", "string", "number", "string", "number"]
        );

        const utf8Length = (str) => i.lengthBytesUTF8(str);

        return (a, b, c = "") => {
            return i.JQenRender(
                a,
                utf8Length(a),
                b,
                utf8Length(b),
                c,
                utf8Length(c)
            );
        };
    });
};
