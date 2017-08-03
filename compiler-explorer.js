(function () {
    var ce_nodes = document.querySelectorAll('.ce');

    for (var i = 0, len = ce_nodes.length; i < len; i++) {
        var element = ce_nodes[i];
        var compiler = "g71";
        var options = "-O1"
        var source = unescape(element.textContent);
        var lines = source.split('\n');
        source = "";
        var displaySource = "";
        var matcher = /^\/\/\/\s*([^:]+):(.*)$/;
        var skipDisplay = false;
        for (var idx = 0; idx < lines.length; ++idx) {
            var line = lines[idx];
            var match = line.match(matcher);
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
        var content = [];
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
        var obj = {
            version: 4,
            content: [{type: 'row', content: content}]
        };
        var ceFragment = encodeURIComponent(JSON.stringify(obj));

        var parent = element.parentElement;
        if (parent.tagName === "PRE") {
            var a = document.createElement('a');
            a.setAttribute('href', 'http://localhost:10240/#' + ceFragment);
            a.setAttribute('target', '_blank');
            a.textContent = 'View';
            parent.parentElement.appendChild(a);
            element.textContent = displaySource;
        } else {
            element.remove();
            var ceElement = document.createElement('iframe');
            ceElement.setAttribute('width', '1200px');
            ceElement.setAttribute('height', '300px');

            var embedUrl = "http://localhost:10240/e#" + ceFragment;
            ceElement.setAttribute('src', embedUrl);
            parent.appendChild(ceElement);
        }
    }

})();