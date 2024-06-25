using System;
using System.Runtime.InteropServices;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;

namespace jogo
{
    public class Game1 : Game
    {
        private GraphicsDeviceManager _graphics;
        private SpriteBatch _spriteBatch;
        private SpriteFont _font;
        private MouseState _previousMouseState;
        private Texture2D _backgroundTexture;
        private GameState _currentGameState;

        // Importar funções do logica.dll (Windows) ou liblogica.so (Linux)
        #if WINDOWS
        [DllImport("logica.dll", CallingConvention = CallingConvention.Cdecl)]
        #else
        [DllImport("liblogica.so", CallingConvention = CallingConvention.Cdecl)]
        #endif
        private static extern int soma(int a, int b);

        #if WINDOWS
        [DllImport("logica.dll", CallingConvention = CallingConvention.Cdecl)]
        #else
        [DllImport("liblogica.so", CallingConvention = CallingConvention.Cdecl)]
        #endif
        private static extern IntPtr mensagem();

        public Game1()
        {
            _graphics = new GraphicsDeviceManager(this);
            Content.RootDirectory = "Content";
            IsMouseVisible = true;
        }

        protected override void Initialize()
        {
            base.Initialize();
            _currentGameState = GameState.MainMenu;
        }

        protected override void LoadContent()
        {
            _spriteBatch = new SpriteBatch(GraphicsDevice);
            _font = Content.Load<SpriteFont>("File");
            _backgroundTexture = Content.Load<Texture2D>("backgroun2");
        }

        protected override void Update(GameTime gameTime)
        {
            if (GamePad.GetState(PlayerIndex.One).Buttons.Back == ButtonState.Pressed || Keyboard.GetState().IsKeyDown(Keys.Escape))
                Exit();

            MouseState currentMouseState = Mouse.GetState();

            switch (_currentGameState)
            {
                case GameState.MainMenu:
                    UpdateMainMenu(currentMouseState);
                    break;
                case GameState.DifficultySelection:
                    UpdateDifficultySelection(currentMouseState);
                    break;
                case GameState.Playing:
                    UpdatePlaying(currentMouseState);
                    break;
            }

            _previousMouseState = currentMouseState;
            base.Update(gameTime);
        }

        private void UpdateMainMenu(MouseState currentMouseState)
        {
            Rectangle enterButton = new Rectangle(GraphicsDevice.Viewport.Width / 2 - 50, GraphicsDevice.Viewport.Height / 2, 100, 30);
            Rectangle exitButton = new Rectangle(GraphicsDevice.Viewport.Width / 2 - 50, GraphicsDevice.Viewport.Height / 2 + 40, 100, 30);

            if (currentMouseState.LeftButton == ButtonState.Pressed && _previousMouseState.LeftButton == ButtonState.Released)
            {
                if (enterButton.Contains(currentMouseState.Position))
                {
                    _currentGameState = GameState.DifficultySelection;
                }
                else if (exitButton.Contains(currentMouseState.Position))
                {
                    Exit();
                }
            }
        }

        private void UpdateDifficultySelection(MouseState currentMouseState)
        {
            Rectangle easyButton = new Rectangle(GraphicsDevice.Viewport.Width / 2 - 50, GraphicsDevice.Viewport.Height / 2, 100, 30);
            Rectangle mediumButton = new Rectangle(GraphicsDevice.Viewport.Width / 2 - 50, GraphicsDevice.Viewport.Height / 2 + 40, 100, 30);
            Rectangle hardButton = new Rectangle(GraphicsDevice.Viewport.Width / 2 - 50, GraphicsDevice.Viewport.Height / 2 + 80, 100, 30);

            if (currentMouseState.LeftButton == ButtonState.Pressed && _previousMouseState.LeftButton == ButtonState.Released)
            {
                if (easyButton.Contains(currentMouseState.Position))
                {
                    IniciarJogo("facil");
                }
                else if (mediumButton.Contains(currentMouseState.Position))
                {
                    IniciarJogo("medio");
                }
                else if (hardButton.Contains(currentMouseState.Position))
                {
                    IniciarJogo("dificil");
                }
            }
        }

        private void UpdatePlaying(MouseState currentMouseState)
        {
            // Exemplo de lógica para atualizar pontuação e vidas
            ProcessarRespostaJogador("resposta do jogador");
        }

        protected override void Draw(GameTime gameTime)
        {
            _spriteBatch.Begin();

            _spriteBatch.Draw(_backgroundTexture, new Rectangle(0, 0, GraphicsDevice.Viewport.Width, GraphicsDevice.Viewport.Height), Color.White);

            switch (_currentGameState)
            {
                case GameState.MainMenu:
                    DrawMainMenu();
                    break;
                case GameState.DifficultySelection:
                    DrawDifficultySelection();
                    break;
                case GameState.Playing:
                    // Desenhar elementos do estado de jogo
                    break;
            }

            _spriteBatch.End();

            base.Draw(gameTime);
        }

        private void DrawMainMenu()
        {
            string titleText = "NexusNumbers";
            Vector2 titleSize = _font.MeasureString(titleText);
            Vector2 titlePosition = new Vector2((GraphicsDevice.Viewport.Width - titleSize.X) / 2, GraphicsDevice.Viewport.Height / 4);
            _spriteBatch.DrawString(_font, titleText, titlePosition, Color.White);

            string enterText = "Entrar";
            Vector2 enterSize = _font.MeasureString(enterText);
            Vector2 enterPosition = new Vector2((GraphicsDevice.Viewport.Width - enterSize.X) / 2, GraphicsDevice.Viewport.Height / 2);
            _spriteBatch.DrawString(_font, enterText, enterPosition, Color.DeepPink);

            string exitText = "Sair";
            Vector2 exitSize = _font.MeasureString(exitText);
            Vector2 exitPosition = new Vector2((GraphicsDevice.Viewport.Width - exitSize.X) / 2, GraphicsDevice.Viewport.Height / 2 + 40);
            _spriteBatch.DrawString(_font, exitText, exitPosition, Color.White);
        }

        private void DrawDifficultySelection()
        {
            string difficultyText = "Escolha a dificuldade";
            Vector2 difficultySize = _font.MeasureString(difficultyText);
            Vector2 difficultyPosition = new Vector2((GraphicsDevice.Viewport.Width - difficultySize.X) / 2, GraphicsDevice.Viewport.Height / 4);
            _spriteBatch.DrawString(_font, difficultyText, difficultyPosition, Color.White);

            string easyText = "Facil";
            Vector2 easySize = _font.MeasureString(easyText);
            Vector2 easyPosition = new Vector2((GraphicsDevice.Viewport.Width - easySize.X) / 2, GraphicsDevice.Viewport.Height / 2);
            _spriteBatch.DrawString(_font, easyText, easyPosition, Color.Orange);

            string mediumText = "Medio";
            Vector2 mediumSize = _font.MeasureString(mediumText);
            Vector2 mediumPosition = new Vector2((GraphicsDevice.Viewport.Width - mediumSize.X) / 2, GraphicsDevice.Viewport.Height / 2 + 40);
            _spriteBatch.DrawString(_font, mediumText, mediumPosition, Color.LimeGreen);

            string hardText = "Dificil";
            Vector2 hardSize = _font.MeasureString(hardText);
            Vector2 hardPosition = new Vector2((GraphicsDevice.Viewport.Width - hardSize.X) / 2, GraphicsDevice.Viewport.Height / 2 + 80);
            _spriteBatch.DrawString(_font, hardText, hardPosition, Color.DeepPink);
        }

        // Método para iniciar o jogo com uma dificuldade específica
        private void IniciarJogo(int nivel)
        {
            // Chama a função nativa via P/Invoke
            // Certifique-se de que 'soma' é chamada aqui, não recursivamente
            int resultado = soma(nivel, 0);
        }

        // Método para processar a resposta do jogador
        private void ProcessarRespostaJogador(string resposta)
        {
            // Chama a função nativa via P/Invoke
            // Certifique-se de que 'mensagem' é chamada aqui, não recursivamente
            IntPtr mensagemPtr = mensagem();
            string mensagemStr = Marshal.PtrToStringAnsi(mensagemPtr);
        }
    }

//estado do jogo//dificuldade
    public enum GameState
    {
        MainMenu,
        DifficultySelection,
        Playing
    }
}
