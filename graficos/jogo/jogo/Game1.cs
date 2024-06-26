using Microsoft.Xna.Framework;
using System;
using System.Runtime.InteropServices;
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
        private Texture2D _loadingTexture; // Textura da tela de carregamento
        private GameState _currentGameState;
        private bool _isLoading; // Variável para controlar se a tela de carregamento está ativa
        private float _loadingTimer; // Timer para controlar o tempo de exibição da tela de carregamento
        private const float LoadingTime = 15f; // Tempo de carregamento em segundos

        [DllImport("logica.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void iniciarJogo(string nomeJogador, char nivelDoJogo);

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
            _isLoading = false;
            _loadingTimer = 0f;
        }

        protected override void LoadContent()
        {
            _spriteBatch = new SpriteBatch(GraphicsDevice);
            _font = Content.Load<SpriteFont>("File");
            _backgroundTexture = Content.Load<Texture2D>("backgroun2");
            _loadingTexture = Content.Load<Texture2D>("loading_screen"); // Carrega a textura da tela de carregamento
        }

        protected override void Update(GameTime gameTime)
        {
            if (GamePad.GetState(PlayerIndex.One).Buttons.Back == ButtonState.Pressed || Keyboard.GetState().IsKeyDown(Keys.Escape))
                Exit();

            MouseState currentMouseState = Mouse.GetState();

            if (_isLoading)
            {
                // Atualiza o timer da tela de carregamento
                _loadingTimer += (float)gameTime.ElapsedGameTime.TotalSeconds;

                // Se o timer exceder o tempo de carregamento, muda para o estado de jogo
                if (_loadingTimer >= LoadingTime)
                {
                    _isLoading = false;
                    // Inicia o jogo na dificuldade selecionada
                    switch (_currentGameState)
                    {
                        case GameState.Playing:
                            // Inicia o jogo com a dificuldade selecionada
                            break;
                        default:
                            break;
                    }
                }
            }
            else
            {
                switch (_currentGameState)
                {
                    case GameState.MainMenu:
                        UpdateMainMenu(currentMouseState);
                        break;
                    case GameState.DifficultySelection:
                        UpdateDifficultySelection(currentMouseState);
                        break;
                    case GameState.Playing:
                        // Lógica de jogo em andamento
                        break;
                }
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
                    // Mostra a tela de carregamento ao selecionar a dificuldade "Fácil"
                    _isLoading = true;
                    _loadingTimer = 0f;
                    // Você pode adicionar lógica adicional aqui para iniciar o jogo com a dificuldade fácil
                }
                else if (mediumButton.Contains(currentMouseState.Position))
                {
                    // Mostra a tela de carregamento ao selecionar a dificuldade "Médio"
                    _isLoading = true;
                    _loadingTimer = 0f;
                    // Lógica para iniciar o jogo com a dificuldade média
                }
                else if (hardButton.Contains(currentMouseState.Position))
                {
                    // Mostra a tela de carregamento ao selecionar a dificuldade "Difícil"
                    _isLoading = true;
                    _loadingTimer = 0f;
                    // Lógica para iniciar o jogo com a dificuldade difícil
                }
            }
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
                    // Lógica de jogo aqui
                    break;
            }

            // Se estiver carregando, desenha a tela de carregamento
            if (_isLoading)
            {
                // Desenha a tela de carregamento centralizada
                _spriteBatch.Draw(_loadingTexture, new Vector2((GraphicsDevice.Viewport.Width - _loadingTexture.Width) / 2, (GraphicsDevice.Viewport.Height - _loadingTexture.Height) / 2), Color.White);
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

            string mediumText = "Media";
            Vector2 mediumSize = _font.MeasureString(mediumText);
            Vector2 mediumPosition = new Vector2((GraphicsDevice.Viewport.Width - mediumSize.X) / 2, GraphicsDevice.Viewport.Height / 2 + 40);
            _spriteBatch.DrawString(_font, mediumText, mediumPosition, Color.LimeGreen);

            string hardText = "Dificil";
            Vector2 hardSize = _font.MeasureString(hardText);
            Vector2 hardPosition = new Vector2((GraphicsDevice.Viewport.Width - hardSize.X) / 2, GraphicsDevice.Viewport.Height / 2 + 80);
            _spriteBatch.DrawString(_font, hardText, hardPosition, Color.Purple);
        }
    }
}
