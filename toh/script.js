class Tower {
    constructor(element) {
        this.disks = [];
        this.element = element;
    }

    add(disk) {
        this.disks.push(disk);
        this.element.appendChild(disk);
    }

    remove(disk) {
        this.disks = this.disks.filter(d => d !== disk);
        this.element.removeChild(disk);
    }

    canAdd(disk) {
        if (this.disks.length === 0) return true; // Can add to an empty tower
        return this.disks[this.disks.length - 1].dataset.size > disk.dataset.size; // Check size
    }

    isTopDisk(disk) {
        return this.disks.length > 0 && this.disks[this.disks.length - 1] === disk; // Check if the disk is the topmost
    }

    getTopDisk() {
        return this.disks[this.disks.length - 1]; // Get the topmost disk
    }
}

let selectedDisk = null;
let currentMode = 'player';

function setupGame(diskCount) {
    const source = new Tower(document.getElementById("source"));
    const auxiliary = new Tower(document.getElementById("auxiliary"));
    const sink = new Tower(document.getElementById("sink"));

    // Clear any previous disks
    source.disks = [];
    auxiliary.disks = [];
    sink.disks = [];
    document.getElementById("source").innerHTML = '';
    document.getElementById("auxiliary").innerHTML = '';
    document.getElementById("sink").innerHTML = '';

    // Initialize disks on the source tower
    for (let i = diskCount; i >= 1; i--) {
        const disk = document.createElement("div");
        disk.classList.add("disk");
        disk.dataset.size = i;
        disk.draggable = true;

        disk.addEventListener("dragstart", () => {
            selectedDisk = disk;
        });

        source.add(disk);
    }

    // Add event listeners to each tower for drag and drop
    [source, auxiliary, sink].forEach(tower => {
        tower.element.addEventListener("dragover", event => {
            event.preventDefault();
        });

        tower.element.addEventListener("drop", () => {
            if (selectedDisk) {
                const fromTower = selectedDisk.parentElement.towerInstance;
                if (currentMode === 'player') {
                    // Check if the selected disk is the top disk on the source tower
                    if (fromTower.isTopDisk(selectedDisk)) {
                        // Check if the tower can accept the disk
                        if (tower.canAdd(selectedDisk)) {
                            fromTower.remove(selectedDisk);
                            tower.add(selectedDisk);
                        }
                    }
                } else if (currentMode === 'coach') {
                    // In coach mode, move the disk without restrictions
                    fromTower.remove(selectedDisk);
                    tower.add(selectedDisk);
                }

                selectedDisk = null; // Reset selected disk
            }
        });
    });

    // Attach tower instances to each HTML element
    document.getElementById("source").towerInstance = source;
    document.getElementById("auxiliary").towerInstance = auxiliary;
    document.getElementById("sink").towerInstance = sink;
}

// Function to handle disk count selection
document.getElementById("disk-count").addEventListener("change", (event) => {
    const diskCount = parseInt(event.target.value);
    setupGame(diskCount);
});

// Function to handle mode selection
document.getElementById("game-mode").addEventListener("change", (event) => {
    currentMode = event.target.value;
    const diskCount = parseInt(document.getElementById("disk-count").value);
    setupGame(diskCount);
});

// Set default disk count to 3 and invoke the setupGame function
document.getElementById("disk-count").value = 3; // Set dropdown to 3
setupGame(3); // Setup the game with 3 disks
