if [[ $# -eq 0 ]] ; then
    echo "=> Intalling Pycparser"
    pip3 install Pycparser==2.20
    echo 

    echo "=> Installing CProcessor in $HOME/.local/lib/python3.6/site-packages"
    if cp -r CProcessor $HOME/.local/lib/python3.6/site-packages ; then
        echo "CProcessor installed successfully"
    else
        echo "Could not copy CProcessor to $HOME/.local/lib/python3.6/site-packages"
        exit 1
    fi
    echo
    echo "Use ./install -u to uninstall"
    exit 0
fi


case "$1" in
    -u) echo "=> Uninstalling CProcessor"
        if rm -r $HOME/.local/lib/python3.6/site-packages/CProcessor ; then
            echo "CProcessor uninstalled successfully"
            exit 0
        else 
            echo "CProcessor not found in $HOME/.local/lib/python3.6/site-packages/CProcessor"
            exit 1
        ;;
esac