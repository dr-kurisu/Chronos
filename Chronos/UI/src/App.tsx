import "./App.css";
import Router from "./router";
import { AuthProvider } from "./auth/authProvider";

function App()
{
    return (
        <AuthProvider>
            <Router />
        </AuthProvider>
    );
}

export default App;