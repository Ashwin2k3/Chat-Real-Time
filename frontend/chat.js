// Create a new WebSocket connection
const socket = new WebSocket('ws://localhost:8080');

// DOM elements
const chatBox = document.getElementById('chat-box');
const messageInput = document.getElementById('message-input');
const sendButton = document.getElementById('send-button');

// Add an event listener for incoming WebSocket messages
socket.addEventListener('message', function (event) {
    // Create a new message element
    const messageElement = document.createElement('div');
    messageElement.classList.add('message');
    messageElement.textContent = `Server: ${event.data}`;
    
    // Append the message to the chat box
    chatBox.appendChild(messageElement);
    
    // Scroll chat to the bottom when a new message is added
    chatBox.scrollTop = chatBox.scrollHeight;
});

// Send a message when the user clicks the "Send" button
sendButton.addEventListener('click', function () {
    sendMessage();
});

// Send a message when the user presses "Enter"
messageInput.addEventListener('keydown', function (event) {
    if (event.key === 'Enter') {
        sendMessage();
    }
});

function sendMessage() {
    const message = messageInput.value.trim();
    
    if (message) {
        // Send the message through the WebSocket
        socket.send(message);
        
        // Display the message in the chat box
        const messageElement = document.createElement('div');
        messageElement.classList.add('message', 'my-message');
        messageElement.textContent = `Me: ${message}`;
        
        chatBox.appendChild(messageElement);
        
        // Clear the input field
        messageInput.value = '';
        
        // Scroll chat to the bottom
        chatBox.scrollTop = chatBox.scrollHeight;
    }
}

// Handle WebSocket errors
socket.addEventListener('error', function (error) {
    console.error('WebSocket error:', error);
});

// Handle WebSocket connection open event
socket.addEventListener('open', function () {
    console.log('WebSocket connection established.');
});

// Handle WebSocket connection close event
socket.addEventListener('close', function () {
    console.log('WebSocket connection closed.');
});

