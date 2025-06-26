const LoadJQenRender = () => {
    return JQenModule().then((i) => {
        i.JQenRender = i.cwrap(
            "JQenRender",
            "string",
            ["string", "number", "string", "number", "string", "number"]
        );

        return (a, b, c = "") => {
            return i.JQenRender(
                a,
                a.length,
                b,
                b.length,
                c,
                c.length
            );
        };
    });
};
