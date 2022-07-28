;function initNavigationMenu (switchId, menuContainerId) {
    const switcher = document.getElementById(switchId);
    const container = document.getElementById(menuContainerId);


    switcher.addEventListener('click', changeNavigationState);
    

    function changeNavigationState () {
        if (container.classList.contains('open')) {
            container.classList.remove('open');
        }
        else {
            container.classList.add('open');
        }
    }
};