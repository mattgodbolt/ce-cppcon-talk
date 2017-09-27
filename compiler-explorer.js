(function () {
    const ce_nodes = document.querySelectorAll('.ce');

    for (let i = 0, len = ce_nodes.length; i < len; i++) {
        let element = ce_nodes[i];
        let compiler = "g71";
        let options = "-O1"
        let source = unescape(element.textContent);
        let lines = source.split('\n');
        source = "";
        let displaySource = "";
        let matcher = /^\/\/\/\s*([^:]+):(.*)$/;
        let skipDisplay = false;
        for (let idx = 0; idx < lines.length; ++idx) {
            let line = lines[idx];
            let match = line.match(matcher);
            if (match) {
                compiler = match[1];
                options = match[2];
            } else if (line.trim() !== "") {
                if (line === "// setup") {
                    skipDisplay = true;
                } else if (line[0] != ' ') {
                    skipDisplay = false;
                }

                source += line + "\n";
                if (!skipDisplay)
                    displaySource += line + "\n"
            }
        }
        let content = [];
        content.push({
            type: 'component',
            componentName: 'codeEditor',
            componentState: {
                id: 1,
                source: source,
                options: {compileOnChange: true, colouriseAsm: true},
                fontScale: 1.6
            }
        });
        content.push({
            type: 'component',
            componentName: 'compiler',
            componentState: {
                source: 1,
                filters: {commentOnly: true, directives: true, intel: true, labels: true, trim: true},
                options: options,
                compiler: compiler,
                fontScale: 1.8
            }
        });
        let obj = {
            version: 4,
            content: [{type: 'row', content: content}]
        };
        let ceFragment = encodeURIComponent(JSON.stringify(obj));

        let parent = element.parentElement;

        const isPdf = !!window.location.search.match(/print-pdf/gi);
        const baseUrl = isPdf ? 'https://gcc.godbolt.org/' : 'http://localhost:10240/';

        if (parent.tagName === "PRE") {
            let a = document.createElement('a');

            a.setAttribute('href', baseUrl + "#" + ceFragment);
            a.setAttribute('target', '_blank');
            a.setAttribute('class', 'view-button');
            a.textContent = 'View';
            parent.parentElement.appendChild(a);
            element.textContent = displaySource;
        } else {
            element.remove();
            let ceElement = document.createElement('iframe');
            ceElement.setAttribute('width', '1200px');
            ceElement.setAttribute('height', '300px');
            parent.appendChild(ceElement);

            let embedUrl = baseUrl + "e#" + ceFragment;
            if (isPdf) {
                ceElement.setAttribute('src', embedUrl);
            } else {
                Reveal.addEventListener('slidechanged', (e) => {
                    if (e.currentSlide.contains(ceElement)) {
                        ceElement.setAttribute('src', embedUrl);
                        Reveal.sync();
                    }
                });
            }
        }
    }
})();
